#include "mbed.h"
#include "MMA8652.h"
 
#include "ble/BLE.h"
#include "KeyboardService.h"

#include "examples_common.h"
#include <cmath>
 
//The micro:bit has a matrixed display, this is a simple way to use some LEDs on it
DigitalOut col9(P0_12, 0);

DigitalOut waiting_led(P0_13);
DigitalOut connected_led(P0_15);

InterruptIn button1(BUTTON_A);
InterruptIn button2(BUTTON_B);

MMA8652 mma(I2C_SDA0, I2C_SCL0);
BLE ble;
KeyboardService *kbdServicePtr;

static const char DEVICE_NAME[] = "micro:bit controller";
static const char SHORT_DEVICE_NAME[] = "handwave";

float g_offset = 1.08;

static void onDisconnect(const Gap::DisconnectionCallbackParams_t *params)
{
    HID_DEBUG("disconnected\r\n");
    connected_led = 0;

    ble.gap().startAdvertising(); // restart advertising
}

static void onConnect(const Gap::ConnectionCallbackParams_t *params)
{
    HID_DEBUG("connected\r\n");
    waiting_led = false;
}

static void waiting() {
    if (!kbdServicePtr->isConnected())
        waiting_led = !waiting_led;
    else
        connected_led = !connected_led;
}

void send_string(const char * c) {
    if (!kbdServicePtr)
        return;

    if (!kbdServicePtr->isConnected()) {
        HID_DEBUG("we haven't connected yet...");
    } else {
        int len = strlen(c);
        kbdServicePtr->printf(c);
        HID_DEBUG("sending %d chars\r\n", len);
    }
}

/*void send_a() {
    send_string("a");
    wait_ms(50);
}

void send_d() {
    send_string("d");
    wait_ms(50);
}*/

void send_key(char * key) {
    send_string(key);
    wait_ms(200);
    }

void send_stuff() {
    send_string("a");
    /*float accel[3];
    mma.acquire_MMA8652_data_g(accel);
    g_offset = accel[0];*/
}

void send_sleep() {
    send_string("l");
}

void send_reset(){
    send_string("i");
}

/**
void sendEvent() {
    float vals[3];
    char theString[40];
    mma.acquire_MMA8652_data_g(vals); //this writes the value of the sensor to vals[]
    theString = getEvent(vals);
    if (theString[0].compare("")) {
        send_string();
    }
}
**/

void send_more_stuff() {
    send_string("d");
}

int main()
{
    mma.MMA8652_config();
    Ticker heartbeat;

    button1.fall(send_sleep);
    button2.fall(send_reset);

    HID_DEBUG("initialising ticker\r\n");

    heartbeat.attach(waiting, 1);

    HID_DEBUG("initialising ble\r\n");
    ble.init();

    ble.gap().onDisconnection(onDisconnect);
    ble.gap().onConnection(onConnect);

    initializeSecurity(ble);

    HID_DEBUG("adding hid service\r\n");
    KeyboardService kbdService(ble);
    kbdServicePtr = &kbdService;

    HID_DEBUG("adding device info and battery service\r\n");
    initializeHOGP(ble);

    HID_DEBUG("setting up gap\r\n");
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::KEYBOARD);
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME,
                                           (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,
                                           (uint8_t *)SHORT_DEVICE_NAME, sizeof(SHORT_DEVICE_NAME));
    ble.gap().setDeviceName((const uint8_t *)DEVICE_NAME);

    HID_DEBUG("advertising\r\n");
    ble.gap().startAdvertising();

    // MOTION DECTECTION CODE STARTS HERE
    float accel[3];
    float prev_accel[3];
    mma.acquire_MMA8652_data_g(accel);
    int ver_motion=0, hor_motion = 0;
    while (true) {        
        ble.waitForEvent();
        
        prev_accel[0] = accel[0];
        prev_accel[1] = accel[1];
        prev_accel[2] = accel[2];
        
        mma.acquire_MMA8652_data_g(accel);
        //if ((prev_accel[0] < -0.6 - g_offset and accel[0] > 0.6 - g_offset) or (prev_accel[0] > 0.6 - g_offset and accel[0] < -0.6 - g_offset)) { // GOING UP OR DOWN
        if (std::abs(accel[0] - prev_accel[0]) > 1){
            ver_motion++;
            send_key("|");
            hor_motion = 0;
        //}else if (prev_accel[0] > 0.25 - g_offset and accel[0] < -0.25 - g_offset) { // GOING DOWN
        //    send_key("fishing");
        }
        //else if ((prev_accel[2] < -0.5 and accel[2] > 0.5) or (prev_accel[2] > 0.5 and accel[2] < -0.5)) { // GOING RIGHT OR LEFT
        else if (std::abs(accel[2] - prev_accel[2]) > 1){
            hor_motion++;
            send_key("---");
            ver_motion = 0;
        }
        //}else if (prev_accel[2] > 0.35 and accel[2] < -0.35) { // GOING LEFT
        //    send_key("wood chopping");            
        if (ver_motion>3){
            send_key("k"); //Eat
            ver_motion = 0;
            hor_motion = 0;
            
        }else if (hor_motion>3){
            send_key("j"); //Build
            ver_motion = 0;
            hor_motion = 0;
        }

        
        

        //sendEvent();
    }
}

/**
char * getEvent(float inpt[3]) {

    float prev_vals[3] = inpt;
    float new_vals[3];
    mma.acquire_MMA8652_data_g(new_vals);
    if (

    return " ";
    
}
**/


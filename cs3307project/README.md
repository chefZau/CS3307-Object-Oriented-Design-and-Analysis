# cs3307mock
This is the CS3307 project!

For all tests:
    Input equal to 100 means sensor detects something!
For test1:
    Test User Mode can work correctly.
    1.get all rooms information
    2.user can enter any input, which simulate the sensor signal
    3.First enter 100, Yellow light on(User Mode is OFF)
    4.Second enter 100, Red light on(User Mode is ON)
    5.Stop

For test2:
    Test Alarm.
    This is used to test alarm!
    User can enter any input. Whenever user enters 100, it will turn on the yellow light(User Mode is OFF)
    Enter Control^C to switch to detect mode(User Mode ON)
    User can enter any input. Whenever user enters 100, it will turn on the red light(User Mode is ON)
    When it raise alarm: 1. User can close alarm
                         2. User can reset alarm
                         3. No response within a specific time, then call emergency.


For test3:
    Test auto switch light function.
    Create 5 rooms.
    Turn auto switch light mode ON for 2 second. Get lights state.
    Turn auto switch light mode OFF and get lights state.


For test4:
    Test get information function.
    Test whether user can receive all the appliance's information.


For test5:
    Test if all the information can update correctly.
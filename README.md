# Arduino Controller Wrapper


## PS3 Controller

#### Crating Instance with USB

You will need to pass the PS3USB instance as a reference as well as a USB instance
While initializing the ControllerPs3 you'll pass the PS3USB to the template, this
will indicate that you are working with a PS3 controller in USB mode.

```c++
USB Usb;
PS3USB PS3(&Usb); // This will just create the instance
ControllerPs3 <PS3USB> ctrl(&Usb, &PS3);

void setup(){
  ctrl.setUp();
}
```

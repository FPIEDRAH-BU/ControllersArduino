# Arduino Controller Wrapper


## PS3 Controller

#### Crating Controller Instance

You will need to pass the PS3USB instance as a reference as well as a USB instance
While initializing the ControllerPs3 you'll pass the PS3USB to the template, this
will indicate that you are working with a PS3 controller in USB mode.

```c++
USB Usb;
PS3USB PS3(&Usb);
ControllerPs3 <PS3USB> ctrl(&Usb, &PS3);

void setup(){
  ctrl.setUp();
}
```

In order to have a PS3 with Bluetooth connection you may modify the initilizer in the
following way:

```c++
USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);
ControllerPs3 <PS3BT> ctrl(&Usb, &PS3);
```

### Getting Data From The Controller

Get buttons in an array:

```c++
ctrl.getButtons();
```

The buttons are in the following order:
```c++
    {UP, RIGHT, DOWN, LEFT, TRIANGLE, CIRCLE,
            CROSS, SQUARE, L2, R2, L1, R1, SELECT, START};
```

you may as well use getButtons16Bit, the function will get you all the array
dumped in to a 16bit integer.

To get the Hats you may use this functions:
```c++
ctrl.getHats();
```

The hats will be returned in the following order:
```c++
{LeftHatX, RightHatX, LeftHatX, LeftHatY};
```



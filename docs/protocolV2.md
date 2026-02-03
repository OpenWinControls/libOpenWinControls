# Controller protocol v2

Used in **win 5**, **win mini 25**.

## Device info

```text
Product ID: 0x2f24
Vendor ID:  0x137

Report descriptor:

Usage Page (FF00h),         ; FF00h, vendor-defined
Usage (01h),
Collection (Application),
    Report ID (1),
    Usage Minimum (01h),
    Usage Maximum (02h),
    Logical Minimum (0),
    Logical Maximum (255),
    Report Size (8),
    Report Count (63),
    Input (Variable),
    Usage Minimum (01h),
    Usage Maximum (02h),
    Logical Minimum (0),
    Logical Maximum (255),
    Report Count (63),
    Output (Variable),
End Collection
```

## Key codes

Keyboard mode uses [HID Usage ID](https://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/translate.pdf) key codes and a few custom special codes.

Custom key codes for keyboard mode:

```text
0xe8 - mousewheel up
0xe9 - mousewheel down
0xea - left mouse
0xeb - right mouse
0xec - middle mouse
0xed - mouse fast move
```

Custom key codes for gamepad mode:

```text
0x8000 - dpad up
0x8001 - dpad down
0x8002 - dpad left
0x8003 - dpad right
0x8004 - start
0x8005 - select
0x8006 - menu
0x8007 - button A
0x8008 - button B
0x8009 - button X
0x800a - button Y
0x800b - L1
0x800c - R1
0x800d - L2
0x800e - R2
0x800f - L3
0x8010 - R3
0x8011 - left stick up
0x8012 - left stick down
0x8013 - left stick left
0x8014 - left stick right
0x8015 - right stick up
0x8016 - right stick down
0x8017 - right stick left
0x8018 - right stick right
```

## Status interrupt

Endpoint 0x81 IN, sent by the controller every 1 second

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th>2</th>
        <th>3</th>
        <th>4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>unk</td>
        <td>unused</td>
        <td>unk ^ 0xff</td>
        <td>unused ^ 0xff</td>
        <td></td>
        <td>version major</td>
        <td>version minor</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>00</td>
        <td>5a</td>
        <td>ff</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

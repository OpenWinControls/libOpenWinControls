# Controller protocol v1

Used in **win 3**, **win max 2**, **win mini 23/24** and **win 4**.

## Device info

```text
Product ID: 0x2f24
Vendor ID:  0x135

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
    Report Count (32),
    Input (Variable),
    Usage Minimum (01h),
    Usage Maximum (02h),
    Logical Minimum (0),
    Logical Maximum (255),
    Report Count (32),
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

## Commands

Mode:

- Read (1)
- Write (2)

Command:

- controller version/init communication (0)
- Read/Write (1)
- Checksum (2)
- Commit (3)

Supported combinations, and their effect, below.

## Packets

### Init communication

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>01</td>
        <td>00</td>
        <td>5a</td>
        <td>0e</td>
        <td>0f</td>
        <td>00</td>
    </tr>
</table>

Response

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xff</td>
        <td>cmd ^ 0xff</td>
        <td></td>
        <td>ready state</td>
        <td>gamepad version minor</td>
        <td>gamepad version major</td>
        <td>keyboard version minor</td>
        <td>keyboard version major</td>
        <td>other bytes</td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>01</td>
        <td>00</td>
        <td>5a</td>
        <td>0e</td>
        <td>0f</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
    </tr>
</table>

Repeat until byte **8** is **0xaa** (ready).

Gamepad version is the xbox360 part of the controller, keyboard is the keyboard/mouse part.

GPD uses the code **Xyyy** for the gamepad and **Kyyy** for the keyboard/mouse in their official app for devices using this protocol.

Example: X408 K407, this is version 4.8 and 4.7.

## Get current config

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>page index</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>01</td>
        <td>01</td>
        <td>5a</td>
        <td>0e</td>
        <td>0e</td>
        <td>00</td>
        <td>00</td>
        <td>00</td>
    </tr>
</table>

Response

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
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20</th>
        <th>21</th>
        <th>22</th>
        <th>23</th>
        <th>24</th>
        <th>25</th>
        <th>26</th>
        <th>27</th>
        <th>28</th>
        <th>29</th>
        <th>30</th>
        <th>31</th>
        <th>32</th>
        <th>33</th>
        <th>34</th>
        <th>35</th>
        <th>36</th>
        <th>37</th>
        <th>38</th>
        <th>39</th>
        <th>40</th>
        <th>41</th>
        <th>42-49</th>
        <th>50</th>
        <th>51</th>
        <th>52</th>
        <th>53</th>
        <th>54</th>
        <th>55</th>
        <th>56</th>
        <th>57</th>
        <th>58</th>
        <th>59</th>
        <th>60</th>
        <th>61</th>
        <th>62</th>
        <th>63</th>
    </tr>
    <tr>
        <td colspan="2">dpad up</td>
        <td colspan="2">dpad down</td>
        <td colspan="2">dpad left</td>
        <td colspan="2">dpad right</td>
        <td colspan="2">A</td>
        <td colspan="2">B</td>
        <td colspan="2">X</td>
        <td colspan="2">Y</td>
        <td colspan="2">left analog up</td>
        <td colspan="2">left analog down</td>
        <td colspan="2">left analog left</td>
        <td colspan="2">left analog right</td>
        <td colspan="2">L3</td>
        <td colspan="2">R3</td>
        <td colspan="2">Start</td>
        <td colspan="2">Select</td>
        <td colspan="2">Menu</td>
        <td colspan="2">L1</td>
        <td colspan="2">R1</td>
        <td colspan="2">L2</td>
        <td colspan="2">R2</td>
        <td></td>
        <td colspan="2">left back button slot 1</td>
        <td colspan="2">left back button slot 2</td>
        <td colspan="2">left back button slot 3</td>
        <td colspan="2">left back button slot 4</td>
        <td colspan="2">right back button slot 1</td>
        <td colspan="2">right back button slot 2</td>
        <td colspan="2">right back button slot 3</td>
    </tr>
    <tr>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
    </tr>
</table>

Sample response using [hidapi](https://github.com/libusb/hidapi):

`1b00 1900 0600 0500 5100 4f00 5000 5200 1a00 1600 0400 0700 2c00 2800 0d00 1200 2900 ea00 eb00 1300 1000 0000 0000 0000 0000 0900 0000 0000 0000 0a00 0000 0000 0000`

keycodes are **uint16_t**.

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>page index</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>01</td>
        <td>01</td>
        <td>5a</td>
        <td>0e</td>
        <td>0e</td>
        <td>00</td>
        <td>01</td>
        <td>00</td>
    </tr>
</table>

Response

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
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12-15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20</th>
        <th>21</th>
        <th>22</th>
        <th>23</th>
        <th>24</th>
        <th>25</th>
        <th>26</th>
        <th>27</th>
        <th>28</th>
        <th>29</th>
        <th>30</th>
        <th>31</th>
        <th>32-63</th>
    </tr>
    <tr>
        <td colspan="2">right back button slot 4</td>
        <td>rumble mode</td>
        <td></td>
        <td>win4 led mode</td>
        <td>win4 led color (R)</td>
        <td>win4 led color (G)</td>
        <td>win4 led color (B)</td>
        <td>left analog center</td>
        <td>left analog boundary</td>
        <td>right analog center</td>
        <td>right analog boundary</td>
        <td></td>
        <td colspan="2">left back button slot 1 delay</td>
        <td colspan="2">left back button slot 2 delay</td>
        <td colspan="2">left back button slot 3 delay</td>
        <td colspan="2">left back button macro delay/hold time</td>
        <td colspan="2">right back button slot 1 delay</td>
        <td colspan="2">right back button slot 2 delay</td>
        <td colspan="2">right back button slot 3 delay</td>
        <td colspan="2">right back button macro delay/hold time</td>
        <td></td>
    </tr>
    <tr>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Deadzone fields are present in latest firmwares for max 2, mini and win4.

Win4 led fields are 0 on other devices.

Configuration does not fit in a single response, use the index to get all parts.

## Checksum for read config

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>01</td>
        <td>02</td>
        <td>5a</td>
        <td>0e</td>
        <td>0d</td>
        <td>00</td>
    </tr>
</table>

Response

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13-23</th>
        <th>24</th>
        <th>25</th>
        <td>26-63</td>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xff</td>
        <td>cmd ^ 0xff</td>
        <td></td>
        <td>ready state</td>
        <td>gamepad version minor</td>
        <td>gamepad version major</td>
        <td>keyboard version minor</td>
        <td>keyboard version major</td>
        <td></td>
        <td colspan="2">checksum</td>
        <td>other bytes</td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>01</td>
        <td>00</td>
        <td>5a</td>
        <td>0e</td>
        <td>0d</td>
        <td>00</td>
        <td>aa</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
    </tr>
</table>

Checksum is the sum of all configuration bytes (whole configuration).

No need to wait for ready state here.

## Prepare for write

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>00</td>
        <td>5a</td>
        <td>0d</td>
        <td>0f</td>
        <td>00</td>
    </tr>
</table>

Response

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xff</td>
        <td>cmd ^ 0xff</td>
        <td></td>
        <td>ready state</td>
        <td>gamepad version minor</td>
        <td>gamepad version major</td>
        <td>keyboard version minor</td>
        <td>keyboard version major</td>
        <td>unk</td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>00</td>
        <td>5a</td>
        <td>0d</td>
        <td>0f</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
    </tr>
</table>

Initialization is successful if byte **8** contains **0xaa**.

## Write config

You must send a total of 256 bytes, each packet is 32 bytes. (8 * 32)

Use the index to specify the packet number.

Writes don't have a response.

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20</th>
        <th>21</th>
        <th>22</th>
        <th>23</th>
        <th>24-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td colspan="2">dpad up</td>
        <td colspan="2">dpad down</td>
        <td colspan="2">dpad left</td>
        <td colspan="2">dpad right</td>
        <td colspan="2">A</td>
        <td colspan="2">B</td>
        <td colspan="2">X</td>
        <td colspan="2">Y</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>00</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20</th>
        <th>21</th>
        <th>22</th>
        <th>23</th>
        <th>24-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td colspan="2">left analog up</td>
        <td colspan="2">left analog down</td>
        <td colspan="2">left analog left</td>
        <td colspan="2">left analog right</td>
        <td colspan="2">L3</td>
        <td colspan="2">R3</td>
        <td colspan="2">start</td>
        <td colspan="2">select</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>01</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td colspan="2">menu</td>
        <td colspan="2">L1</td>
        <td colspan="2">R1</td>
        <td colspan="2">L2</td>
        <td colspan="2">R2</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>02</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20</th>
        <th>21</th>
        <th>22-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td colspan="2">left back button slot 1</td>
        <td colspan="2">left back button slot 2</td>
        <td colspan="2">left back button slot 3</td>
        <td colspan="2">left back button slot 4</td>
        <td colspan="2">right back button slot 1</td>
        <td colspan="2">right back button slot 2</td>
        <td colspan="2">right back button slot 3</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>03</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td colspan="2">right back button slot 4</td>
        <td colspan="2">rumble mode</td>
        <td>win4 led mode</td>
        <td>win4 led color (R)</td>
        <td>win4 led color (G)</td>
        <td>win4 led color (B)</td>
        <td>left analog center</td>
        <td>left analog boundary</td>
        <td>right analog center</td>
        <td>right analog boundary</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>04</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13</th>
        <th>14</th>
        <th>15</th>
        <th>16</th>
        <th>17</th>
        <th>18</th>
        <th>19</th>
        <th>20</th>
        <th>21</th>
        <th>22</th>
        <th>23</th>
        <th>24-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td colspan="2">left back button slot 1 delay</td>
        <td colspan="2">left back button slot 2 delay</td>
        <td colspan="2">left back button slot 3 delay</td>
        <td colspan="2">left back button slot 4 delay</td>
        <td colspan="2">right back button slot 1 delay</td>
        <td colspan="2">right back button slot 2 delay</td>
        <td colspan="2">right back button slot 3 delay</td>
        <td colspan="2">right back button slot 4 delay</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>05</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>06</td>
        <td>00</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5</th>
        <th>6</th>
        <th>7</th>
        <th>8-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
        <td>index</td>
        <td></td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>01</td>
        <td>5a</td>
        <td>0d</td>
        <td>0e</td>
        <td>00</td>
        <td>07</td>
        <td>00</td>
        <td>00</td>
    </tr>
</table>

## Checksum pending written config in memory

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>02</td>
        <td>5a</td>
        <td>0d</td>
        <td>0d</td>
        <td>00</td>
    </tr>
</table>

Response

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-7</th>
        <th>8</th>
        <th>9</th>
        <th>10</th>
        <th>11</th>
        <th>12</th>
        <th>13-23</th>
        <th>24</th>
        <th>25</th>
        <td>26-63</td>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xff</td>
        <td>cmd ^ 0xff</td>
        <td></td>
        <td>ready state</td>
        <td>gamepad version minor</td>
        <td>gamepad version major</td>
        <td>keyboard version minor</td>
        <td>keyboard version major</td>
        <td></td>
        <td colspan="2">checksum</td>
        <td>unk</td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>02</td>
        <td>5a</td>
        <td>0d</td>
        <td>0d</td>
        <td>00</td>
        <td>aa</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
    </tr>
</table>

Checksum is the sum of all configuration bytes (whole configuration).

No need to wait for ready state here.

## Commit configuration to the controller

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th colspan="2">2</th>
        <th>3</th>
        <th colspan="2">4</th>
        <th>5-31</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>const</td>
        <td>mode</td>
        <td>cmd</td>
        <td>const ^ 0xff</td>
        <td>mode ^ 0xf</td>
        <td>cmd ^ 0xf</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>a5</td>
        <td>02</td>
        <td>03</td>
        <td>5a</td>
        <td>0d</td>
        <td>0c</td>
        <td>00</td>
    </tr>
</table>

The controller does not read the configuration from memory,
so it is not possible to create configs on fly in memory to avoid commits.

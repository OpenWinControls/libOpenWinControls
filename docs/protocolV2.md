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
0x8019 - ???
0x801a - ???
0x801b - ???
0x801c - ???
0x801d - ???
0x801e - ???
0x801f - ???
0x8020 - ???
```

## Configuration

Configuration total size is 1024 bytes.

The controller hardware supports up to 4 back buttons, GPD devices have 2 back buttons, thus button 3 and 4 sections can be ignored, even if not empty (default settings).

The back button number **does not name a physical position on device**.

# Status interrupt

Endpoint 0x81 IN, sent by the controller every 1 second.

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
        <td>const</td>
        <td>unused</td>
        <td>const ^ 0xff</td>
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


# Packets

> NOTE:
> 
> The following sections may be inaccurate

Rejected commands return **0xe2** in byte **8**.

Unless stated otherwise, checksum is the sum of all bytes after it.

## Init communication

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th>2-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>21</td>
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
        <th>9-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td>unk</td>
        <td></td>
        <td colspan="2">checksum</td>
        <td>ready state</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>21</td>
        <td>02</td>
        <td>00</td>
        <td>xx</td>
        <td>00</td>
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
        <th>2-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>2b</td>
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
        <th>9-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td>unk</td>
        <td></td>
        <td colspan="2">checksum</td>
        <td>ready state</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>2b</td>
        <td>02</td>
        <td>00</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Successful initialization requires both calls to return **0xaa** in byte **8**.

## Get firmware versions

**unconfirmed, no firmware update to compare, prefer status interrupt.**

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th>2-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>41</td>
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
        <th>14-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td>unk</td>
        <td>unk</td>
        <td colspan="2">checksum</td>
        <td></td>
        <td></td>
        <td>xinput version minor</td>
        <td>xinput version major</td>
        <td>keyboard&mouse version minor</td>
        <td>keyboard&mouse version major</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>41</td>
        <td>10</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Gamepad version is the xbox360 part of the controller, keyboard is the keyboard/mouse part.

## Get current config

After sending the read command, applications must read _(get input report)_ until the end packet is received.

**First** and **last** packets are special and have a different layout.

Send

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
        <th>10-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td></td>
        <td></td>
        <td>unk</td>
        <td></td>
        <td></td>
        <td>unk</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>02</td>
        <td>00</td>
        <td>00</td>
        <td>00</td>
        <td>04</td>
        <td>00</td>
        <td>00</td>
        <td>04</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <th>62-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk12 ^ 0xff</td>
        <td>unk13 ^ 0xff</td>
        <td>unk14 ^ 0xff</td>
        <td>unk15 ^ 0xff</td>
        <td colspan="2">dpad up</td>
        <td colspan="2">dpad left</td>
        <td colspan="2">dpad down</td>
        <td colspan="2">dpad right</td>
        <td colspan="2">start</td>
        <td colspan="2">select</td>
        <td colspan="2">menu</td>
        <td colspan="2">A</td>
        <td colspan="2">B</td>
        <td colspan="2">X</td>
        <td colspan="2">Y</td>
        <td colspan="2">L1</td>
        <td colspan="2">R1</td>
        <td colspan="2">L2</td>
        <td colspan="2">R2</td>
        <td colspan="2">L3</td>
        <td colspan="2">R3</td>
        <td colspan="2">left analog up</td>
        <td colspan="2">left analog down</td>
        <td colspan="2">left analog left</td>
        <td colspan="2">left analog right</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
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
        <th>8-43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td></td>
        <td colspan="2">dpad up (gamepad mode)</td>
        <td colspan="2">dpad down (gamepad mode)</td>
        <td colspan="2">dpad left (gamepad mode)</td>
        <td colspan="2">dpad right (gamepad mode)</td>
        <td colspan="2">start (gamepad mode)</td>
        <td colspan="2">select (gamepad mode)</td>
        <td colspan="2">menu (gamepad mode)</td>
        <td colspan="2">A (gamepad mode)</td>
        <td colspan="2">B (gamepad mode)</td>
        <td colspan="2">X (gamepad mode)</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>38</td>
        <td>00</td>
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
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
        <th>50</th>
        <th>51</th>
        <th>52</th>
        <th>53</th>
        <th>54-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">Y (gamepad mode)</td>
        <td colspan="2">L1 (gamepad mode)</td>
        <td colspan="2">R1 (gamepad mode)</td>
        <td colspan="2">L2 (gamepad mode)</td>
        <td colspan="2">R2 (gamepad mode)</td>
        <td colspan="2">L3 (gamepad mode)</td>
        <td colspan="2">R3 (gamepad mode)</td>
        <td colspan="2">left analog up (gamepad mode)</td>
        <td colspan="2">left analog down (gamepad mode)</td>
        <td colspan="2">left analog left (gamepad mode)</td>
        <td colspan="2">left analog right (gamepad mode)</td>
        <td colspan="2">right analog up (gamepad mode)</td>
        <td colspan="2">right analog down (gamepad mode)</td>
        <td colspan="2">right analog left (gamepad mode)</td>
        <td colspan="2">right analog right (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>70</td>
        <td>00</td>
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
        <th>8-11</th>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td></td>
        <td>back button 1 mode</td>
        <td>back button 1 number of keys</td>
        <td colspan="2">back button 1 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>a8</td>
        <td>00</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>e0</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>18</td>
        <td>01</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>back button 2 mode</td>
        <td>back button 2 number of keys</td>
        <td colspan="2">back button 2 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>50</td>
        <td>01</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>88</td>
        <td>01</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>c0</td>
        <td>01</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>f8</td>
        <td>01</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>back button 3 mode</td>
        <td>back button 3 number of keys</td>
        <td colspan="2">back button 3 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>30</td>
        <td>02</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>68</td>
        <td>02</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>a0</td>
        <td>02</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>back button 4 mode</td>
        <td>back button 4 number of keys</td>
        <td colspan="2">back button 4 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>d8</td>
        <td>02</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>10</td>
        <td>03</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>48</td>
        <td>03</td>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>80</td>
        <td>03</td>
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
        <th>21-24</th>
        <th>25</th>
        <th>26</th>
        <th>27</th>
        <th>28-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>rumble mode</td>
        <td>led control (unused)</td>
        <td>led color (R) (unused)</td>
        <td>led color (G) (unused)</td>
        <td>led color (B) (unused)</td>
        <td>left analog center</td>
        <td>left analog boundary</td>
        <td>right analog center</td>
        <td>right analog boundary</td>
        <td>unused</td>
        <td>analog sticks draw mode</td>
        <td>analog sticks deadzone control</td>
        <td>device emulation mode</td>
        <td>reserved</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>38</td>
        <td>00</td>
        <td>b8</td>
        <td>03</td>
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
        <td>ff</td>
    </tr>
</table>

Response (end packet, 0x10)

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
        <th>8-24</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td>reserved</td>
    </tr>
    <tr>
        <td>01</td>
        <td>44</td>
        <td>10</td>
        <td>00</td>
        <td>f0</td>
        <td>03</td>
        <td>xx</td>
        <td>xx</td>
        <td>ff</td>
    </tr>
</table>

## Prepare for write

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th>2-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>21</td>
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
        <th>9-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td>unk</td>
        <td></td>
        <td colspan="2">checksum</td>
        <td>ready state</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>21</td>
        <td>02</td>
        <td>00</td>
        <td>xx</td>
        <td>00</td>
        <td>xx</td>
        <td>xx</td>
        <td>xx</td>
        <td>00</td>
    </tr>
</table>

Successful initialization returns **0xaa** in byte **8**.

## Write config

Writes don't have a response.

Checksum must be calculated and updated on each write packet.

**First** and **last** packets are special and have a different layout.

### First packet header

Bytes **8**-**19** are copied from first read packet bytes **8**-**19**.

Origin and generation is unknown, so to build a proper write init packet, read the config first.

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <th>62-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk</td>
        <td>unk12 ^ 0xff</td>
        <td>unk13 ^ 0xff</td>
        <td>unk14 ^ 0xff</td>
        <td>unk15 ^ 0xff</td>
        <td colspan="2">dpad up</td>
        <td colspan="2">dpad left</td>
        <td colspan="2">dpad down</td>
        <td colspan="2">dpad right</td>
        <td colspan="2">start</td>
        <td colspan="2">select</td>
        <td colspan="2">menu</td>
        <td colspan="2">A</td>
        <td colspan="2">B</td>
        <td colspan="2">X</td>
        <td colspan="2">Y</td>
        <td colspan="2">L1</td>
        <td colspan="2">R1</td>
        <td colspan="2">L2</td>
        <td colspan="2">R2</td>
        <td colspan="2">L3</td>
        <td colspan="2">R3</td>
        <td colspan="2">left analog up</td>
        <td colspan="2">left analog down</td>
        <td colspan="2">left analog left</td>
        <td colspan="2">left analog right</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
        <th>50</th>
        <th>51</th>
        <th>52</th>
        <th>53</th>
        <th>54-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">Y (gamepad mode)</td>
        <td colspan="2">L1 (gamepad mode)</td>
        <td colspan="2">R1 (gamepad mode)</td>
        <td colspan="2">L2 (gamepad mode)</td>
        <td colspan="2">R2 (gamepad mode)</td>
        <td colspan="2">L3 (gamepad mode)</td>
        <td colspan="2">R3 (gamepad mode)</td>
        <td colspan="2">left analog up (gamepad mode)</td>
        <td colspan="2">left analog down (gamepad mode)</td>
        <td colspan="2">left analog left (gamepad mode)</td>
        <td colspan="2">left analog right (gamepad mode)</td>
        <td colspan="2">right analog up (gamepad mode)</td>
        <td colspan="2">right analog down (gamepad mode)</td>
        <td colspan="2">right analog left (gamepad mode)</td>
        <td colspan="2">right analog right (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td colspan="2">unk button (gamepad mode)</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>70</td>
        <td>00</td>
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
    </tr>
</table>

Send

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
        <th>8-11</th>
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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td></td>
        <td>back button 1 mode</td>
        <td>back button 1 number of keys</td>
        <td colspan="2">back button 1 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>a8</td>
        <td>00</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>e0</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>18</td>
        <td>01</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>back button 2 mode</td>
        <td>back button 2 number of keys</td>
        <td colspan="2">back button 2 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>50</td>
        <td>01</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>88</td>
        <td>01</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>c0</td>
        <td>01</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>f8</td>
        <td>01</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>back button 3 mode</td>
        <td>back button 3 number of keys</td>
        <td colspan="2">back button 3 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>30</td>
        <td>02</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>68</td>
        <td>02</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>a0</td>
        <td>02</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>back button 4 mode</td>
        <td>back button 4 number of keys</td>
        <td colspan="2">back button 4 checksum</td>
        <td colspan="2">key slot 1</td>
        <td colspan="2">key slot 1 start time</td>
        <td colspan="2">key slot 1 hold time</td>
        <td colspan="2">key slot 2</td>
        <td colspan="2">key slot 2 start time</td>
        <td colspan="2">key slot 2 hold time</td>
        <td colspan="2">key slot 3</td>
        <td colspan="2">key slot 3 start time</td>
        <td colspan="2">key slot 3 hold time</td>
        <td colspan="2">key slot 4</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>d8</td>
        <td>02</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 4 start time</td>
        <td colspan="2">key slot 4 hold time</td>
        <td colspan="2">key slot 5</td>
        <td colspan="2">key slot 5 start time</td>
        <td colspan="2">key slot 5 hold time</td>
        <td colspan="2">key slot 6</td>
        <td colspan="2">key slot 6 start time</td>
        <td colspan="2">key slot 6 hold time</td>
        <td colspan="2">key slot 7</td>
        <td colspan="2">key slot 7 start time</td>
        <td colspan="2">key slot 7 hold time</td>
        <td colspan="2">key slot 8</td>
        <td colspan="2">key slot 8 start time</td>
        <td colspan="2">key slot 8 hold time</td>
        <td colspan="2">key slot 9</td>
        <td colspan="2">key slot 9 start time</td>
        <td colspan="2">key slot 9 hold time</td>
        <td colspan="2">key slot 10</td>
        <td colspan="2">key slot 10 start time</td>
        <td colspan="2">key slot 10 hold time</td>
        <td colspan="2">key slot 11</td>
        <td colspan="2">key slot 11 start time</td>
        <td colspan="2">key slot 11 hold time</td>
        <td colspan="2">key slot 12</td>
        <td colspan="2">key slot 12 start time</td>
        <td colspan="2">key slot 12 hold time</td>
        <td colspan="2">key slot 13</td>
        <td colspan="2">key slot 13 start time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>10</td>
        <td>03</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 13 hold time</td>
        <td colspan="2">key slot 14</td>
        <td colspan="2">key slot 14 start time</td>
        <td colspan="2">key slot 14 hold time</td>
        <td colspan="2">key slot 15</td>
        <td colspan="2">key slot 15 start time</td>
        <td colspan="2">key slot 15 hold time</td>
        <td colspan="2">key slot 16</td>
        <td colspan="2">key slot 16 start time</td>
        <td colspan="2">key slot 16 hold time</td>
        <td colspan="2">key slot 17</td>
        <td colspan="2">key slot 17 start time</td>
        <td colspan="2">key slot 17 hold time</td>
        <td colspan="2">key slot 18</td>
        <td colspan="2">key slot 18 start time</td>
        <td colspan="2">key slot 18 hold time</td>
        <td colspan="2">key slot 19</td>
        <td colspan="2">key slot 19 start time</td>
        <td colspan="2">key slot 19 hold time</td>
        <td colspan="2">key slot 20</td>
        <td colspan="2">key slot 20 start time</td>
        <td colspan="2">key slot 20 hold time</td>
        <td colspan="2">key slot 21</td>
        <td colspan="2">key slot 21 start time</td>
        <td colspan="2">key slot 21 hold time</td>
        <td colspan="2">key slot 22</td>
        <td colspan="2">key slot 22 start time</td>
        <td colspan="2">key slot 22 hold time</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>48</td>
        <td>03</td>
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
    </tr>
</table>

Send

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
        <th>42</th>
        <th>43</th>
        <th>44</th>
        <th>45</th>
        <th>46</th>
        <th>47</th>
        <th>48</th>
        <th>49</th>
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
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 23</td>
        <td colspan="2">key slot 23 start time</td>
        <td colspan="2">key slot 23 hold time</td>
        <td colspan="2">key slot 24</td>
        <td colspan="2">key slot 24 start time</td>
        <td colspan="2">key slot 24 hold time</td>
        <td colspan="2">key slot 25</td>
        <td colspan="2">key slot 25 start time</td>
        <td colspan="2">key slot 25 hold time</td>
        <td colspan="2">key slot 26</td>
        <td colspan="2">key slot 26 start time</td>
        <td colspan="2">key slot 26 hold time</td>
        <td colspan="2">key slot 27</td>
        <td colspan="2">key slot 27 start time</td>
        <td colspan="2">key slot 27 hold time</td>
        <td colspan="2">key slot 28</td>
        <td colspan="2">key slot 28 start time</td>
        <td colspan="2">key slot 28 hold time</td>
        <td colspan="2">key slot 29</td>
        <td colspan="2">key slot 29 start time</td>
        <td colspan="2">key slot 29 hold time</td>
        <td colspan="2">key slot 30</td>
        <td colspan="2">key slot 30 start time</td>
        <td colspan="2">key slot 30 hold time</td>
        <td colspan="2">key slot 31</td>
        <td colspan="2">key slot 31 start time</td>
        <td colspan="2">key slot 31 hold time</td>
        <td colspan="2">key slot 32</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>80</td>
        <td>03</td>
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
    </tr>
</table>

Send

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
        <th>21-24</th>
        <th>25</th>
        <th>26</th>
        <th>27</th>
        <th>28-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td colspan="2">key slot 32 start time</td>
        <td colspan="2">key slot 32 hold time</td>
        <td>rumble mode</td>
        <td>led control (unused)</td>
        <td>led color (R) (unused)</td>
        <td>led color (G) (unused)</td>
        <td>led color (B) (unused)</td>
        <td>left analog center</td>
        <td>left analog boundary</td>
        <td>right analog center</td>
        <td>right analog boundary</td>
        <td>unused</td>
        <td>analog sticks draw mode</td>
        <td>analog sticks deadzone control</td>
        <td>device emulation mode</td>
        <td>reserved</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>38</td>
        <td>00</td>
        <td>b8</td>
        <td>03</td>
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
        <td>ff</td>
    </tr>
</table>

Send (end packet, 0x10)

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
        <th>8-24</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td colspan="2">page index</td>
        <td colspan="2">checksum</td>
        <td>reserved</td>
    </tr>
    <tr>
        <td>01</td>
        <td>43</td>
        <td>10</td>
        <td>00</td>
        <td>f0</td>
        <td>03</td>
        <td>xx</td>
        <td>xx</td>
        <td>ff</td>
    </tr>
</table>

## Commit configuration to the controller

Send

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
        <th>10-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td>unk</td>
        <td></td>
        <td></td>
        <td></td>
        <td colspan="2">checksum</td>
        <td></td>
        <td>unk</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>27</td>
        <td>2</td>
        <td>00</td>
        <td>00</td>
        <td>00</td>
        <td>04</td>
        <td>00</td>
        <td>00</td>
        <td>04</td>
        <td>00</td>
    </tr>
</table>

Send

<table>
    <tr>
        <th>0</th>
        <th>1</th>
        <th>2-63</th>
    </tr>
    <tr>
        <td>ID</td>
        <td>cmd</td>
        <td></td>
    </tr>
    <tr>
        <td>01</td>
        <td>22</td>
        <td>00</td>
    </tr>
</table>

# Sensorcli

Sensorcli is a command line interface used to receive data and control firmware from a computer when the dynamic protocol is being implemented. Arguments are optional and can be listed with `--help`.

In the context of sensorcli, the word "sensor" designates the various firmware outputs and can represent raw sensor data or algorithm's outputs.

## Commands

The full list of available commands can be retrieved with the `help` command. The following table lists the most useful ones.

Arguments within brackets (`[arg]`) are optional.

| <div style="width:280px">Command</div> | Description |
| -------------------------------------- | --- |
| `help [command]`                       | If `command` is not provided, list all available commands.<br/> Otherwise, provide details about the requested command.  |
| `ids`                                  | List sensor type to be used in other command (designated by `sensor_name`). <br/>Commonly used ids are:<ul><li>`racc` for raw accel</li><li>`rgyr` for raw gyro</li><li>`rtemp` for raw temperature</li><li>`rmag` for raw mag</li><li>`acc` for calibrated accel</li><li>`gyr` for calibrated gyro</li><li>`temp` for calibrated temperature</li><li>`mag` for calibrated mag</li><li>`grv` for game rotation vector (6-axis fusion)</li><li>`rv` for rotation vector (9-axis fusion)</li></ul> |
| `en sensor_name`                       | Enable the sensor designated by `sensor_name` |
| `dis sensor_name`                      | Disable the sensor designated by `sensor_name` |
| `ping`                                 | Interrogates firmware and lists all available sensors. |
| `disp off [sensor_name]`               | Stop displaying sensor data. If `sensor_name` is provided, only the specified sensor data will stop being displayed. If no argument is provided, all sensors data will stop being displayed.<br/>Note: This doesn't disable sensors, it only stops printing them on the console. |
| `disp on [sensor_name]`                | Start displaying sensor data. If `sensor_name` is provided, only the specified sensor data will start being displayed. If no argument is provided, all sensors data will start being displayed. |
| `log on [filename]`                    | Log sensor data to a file.<br/>If `filename` is not specified a file named log_yyyy-mm-dd-H-M-S.txt will be created.<br/>If `filename` is specified sensor events will be logged to this file, overwriting its content.<br/>If `filename` does not exist, it will be created.<br/>Note: To log reliably, it is recommended to turn off display of data in the console (`disp off`). |
| `log off`                              | Stop logging sensor data and properly close the file. |
| `cube on sensor_name`                  | Display a cube whose orientation is based on `sensor_name` data (must be a quaternion).<br/>Note: In order for the cube to receive data, `sensor_name` must be enabled using `en sensor_name` command.<br/> Tip: Turning off the display of data in the console (`disp off`) might smoothen the movement of the cube. |
| `cube off sensor_name`                 | Stop displaying the cube for the specified sensor. |
| `cube setref sensor_name`              | Set the current orientation as reference for the cube for the specified sensor. |
| `cube resetref sensor_name`            | Clear the reference for the cube for the specified sensor. |
| `setconfig sensor_name settings=value` | Set a certain configuration for the requested sensor. Supported configuration depends on the firmware, please refer to the application documentation for the full list. |
| `decode sensor_name descriptor`        | Tell sensor-cli how to decode a custom sensor event.<br/>`descriptor` consists in a string composed of one or more tokens separated by spaces.<br/>Tokens must follows the pattern: `[#\|-\|*]{f\|flt\|float\|d\|dbl\|double\|{s\|sint\|int\|u\|uint}[XX][qYY][_t]}[le\|be][[ZZ]\|\@ZZ]` in which: <ul><li>`[ AAA ]` means AAA is optional</li><li>`{ AAA \| BBB \| ... }` means it's a choice between AAA, BBB, ...</li><li>`[ AAA \| BBB \| ... ]` means it's an optional choice between AAA, BBB, ...</li><li>`#` / `*` / `-` means element should not be returned (useful to indicate padding)</li><li>`f` / `flt` / `float` stands for float (assuming 4 bytes long)</li><li>`d` / `dbl` / `double` stands for double (assuming 8 bytes long)</li><li>`sXX` / `sintXX` / `intXX` / `int` stands for signed integer</li><li>`uXX` / `uintXX` / `uint` stands for unsigned integer</li><li>`XX` is the integer length in bits and can be 8, 16, 24, 32, 40, 48, 56, 64 (assuming 32 as default)</li><li>`qYY` designates the fractional part of a fix point integer</li><li>`le`, `be` indicates endianness used for encoding (assuming LE as default)</li><li>`[ZZ]` or `\@ZZ` indicates number of elements to consider being coded the same way</li></ul> Integer types can be suffixed with `_t` in order to be compatible with `<stdint.h>` types. <br/>Empty descriptor will reset the decoding to default decoder. |
| `sleep ms`                             | Pause the main thread for `ms` millisecond. |
| `quit` or `exit`                       | Properly exit sensorcli. |

## Usage

### Start a log 

Scenario: log raw accel, raw gyro and 6-axis fusion output for 1 min.
```
sensor-cli> disp off; log on my_filename.txt; en racc; en rgyr; en grv; sleep 60000; log off
```

### Display cube

Scenario: Visualize 6-axis fusion output with the cube.
```
sensor-cli> disp off; cube on grv; en grv;
```





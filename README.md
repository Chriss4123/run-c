# run-c
Compile and run/debug C or C++ code easily.

## Installation and Updating
### Install & Update Script

To **install** or **update** run-c, you should run the installation script. To do that, you can either download and run the script manually, or use the following cURL command:
```sh
curl -o- https://raw.githubusercontent.com/Chriss4123/run-c/main/installrun.sh | cat > installrun.sh && sudo bash installrun.sh && rm installrun.sh
```
Running the above command downloads a shell script and runs it. This script clones the **Run C** file to your computer, automatically builds it and then appends the built file to **/usr/bin/run**. Because of this, it requires **sudo** permission. This doesn't stop you from manually downloading the C file and building it yourself if you don't need it in **/usr/bin/run**.

After installation, you will be able to use the **run** command and use the **help** paramater to get information about the script.

Paramaters: [sudo] (run said file with sudo permission) [run] [-d] (debug mode) [file].c(pp) [params] (params to be parsed to file.c(pp))

## You are free to modify and redistribute this script.
Written by Chriss4123

If you would like to see me write more scripts like this one, please star this repo.

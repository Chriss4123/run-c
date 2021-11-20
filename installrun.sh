# https://raw.githubusercontent.com/Chriss4123/run-c/main/run.c?token=AUY3C66YL42WAYALNHEDKJ3BTFJTU

if [[ "$EUID" != 0 ]]
then
    echo "Sudo permission is required to install this program.";
    exit;
fi

declare cinstalled=0;
declare install=0;
declare installed=0;

function Exit() {

    if [ $cinstalled == 1 ]
        then
            sudo rm -f -rf runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X.c
    fi 

    if [ $install == 1 ]
        then
            sudo rm -f -rf runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X
    fi

    if [ $installed == 1 ]
        then
            sudo rm -f -rf /usr/bin/run
    fi

printf "Done cleaning up.\n"

exit;

}

if test -f "/usr/bin/make"
then
    declare gccexists=1;
else
    printf "\nmake not found, but can be installed with: \n\nsudo apt install make\n\n";
    Exit;
fi

declare ins=0;

function sigInt() {
    ((ins=$ins+1))

    if [ $ins == 1 ]
    then
        printf "\nCleaning up...\n";
        printf "\nPress ^C one more time to force quit.\n";
        Exit;
    else
       printf "\n";
       exit;
       return -1;
    fi
    
}

trap 'sigInt' SIGINT

function userInput() {
    read;

    if [ ${REPLY} == "y" ] || [ ${REPLY} == "n" ]
    then
        if [ ${REPLY} == "y" ]
        then
            return 1;
        else
            return 0;
        fi
    else
        echo "$1";
        userInput "$1";
    fi

}

function makeFile() {
            sudo rm -f -rf /usr/bin/palindrome
            sudo rm -f -rf runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X.c
            sudo rm -f -rf runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X
            touch "runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X.c";
            cinstalled=1;
            curl -o- -s "https://raw.githubusercontent.com/Chriss4123/run-c/main/run.c" | cat > runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X.c
            echo "Download complete";
            install=1;
            make -s runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X;
            echo "Compiling complete";
            installed=1;
            sudo cp -f runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X /usr/bin/run
            echo "File appended";
            installed=0;

            echo "Cleaning up...";
            rm runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X.c;
            cinstalled=0;
            rm runnPLnAoU0dTkoGCn46Eg3hllLK0Cm3AOk6smcLExaTKujuOEfkmw4f3v2sEIkCVvNWmmhOQQCEJRhJcdk2mWa6pkOsPHGi9pBty6X;
            install=0;
            echo "Done cleaning up";
            exit;
}

FILE=/usr/bin/run
if test -f "$FILE"; then
    echo "File $FILE exists. Overwrite? y/n";
    userInput "Invalid input. Overwrite file? y/n";
    if [ $? == 1 ]
        then
            makeFile;
        
        else
            printf "Sorry to see you go!\n";
            Exit;
    fi
else

makeFile;

fi

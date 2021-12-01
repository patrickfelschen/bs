#!/bin/bash

function pathExists {
        if test -a $DIR; then
                echo "Pfad exisitiert."
        else
                echo "Pfad existiert nicht."
        fi
}

function fileOrDir {
        if test -d $DIR; then
                echo "Es handelt sich um ein Verzeichnis."
        elif test -f $DIR; then
                echo "Es handelt sich um eine Datei."
        fi
}

function isSymbolicLink {
        if test -L $DIR; then
                echo "Es handelt sich um einen symbolischen Link."
        fi
}

function isOwner {
        if test -O $DIR; then
                echo "Aufrufer ist Besitzer"
        else
                echo "Aufrufer ist nicht Besitzer"
        fi
}

function printOwner {
        echo "Besitzer: " $(stat -c '%U' $DIR)
}

function checkExtension {
        if [ "${DIR: -4}" == ".txt" ]; then
                echo "Datei hat Endung .txt"
                echo "Soll die Datei geöffnet werden? (yes/no)"
                read command
                while [ "$command" != "y" ] && [ "$command" != "yes" ] && [ "$command" != "n" ] && [ "$command" != "no" ];
		do
			echo "Soll die Datei geöffnet werden? (yes/no)"
                        read command
                done

                if [ "$command" == "y" ]; then
                        nano "$DIR"
                fi

        else
                echo "Datei hat keine .txt Endung"
        fi
}


for DIR in "$@"
do
        echo "Angegebener Pfad: $DIR"
        pathExists /bin/bash
        fileOrDir /bin/bash
        isSymbolicLink /bin/bash
        isOwner /bin/bash
        printOwner /bin/bash
        checkExtension /bin/bash
done

exit 0

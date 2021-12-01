#!/bin/bash

echo "Bitte Pfad angeben: "
read DIR
echo "Angegebener Pfad: $DIR"

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

pathExists /bin/bash
fileOrDir /bin/bash
isSymbolicLink /bin/bash
isOwner /bin/bash
printOwner /bin/bash

exit 0

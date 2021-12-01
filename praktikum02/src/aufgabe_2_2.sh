#!/bin/bash

function pathExists {
        if test $DIR; then
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


for DIR in "$@"
do
	echo "Angegebener Pfad: $DIR"
	pathExists /bin/bash
	fileOrDir /bin/bash
	isSymbolicLink /bin/bash
	isOwner /bin/bash
	printOwner /bin/bash
done

exit 0

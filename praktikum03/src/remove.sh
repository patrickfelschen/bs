#!/bin/bash

TRASH="$HOME/.trashBin"
DIR="$HOME/.trashBin/.dir"

function createTrashFolder {
	if [ -d $TRASH ]; then
		echo "Trash existiert bereits"
	else
		mkdir $TRASH
		if [ -d $TRASH ]; then
			echo "Trash wurde erfolgreich erstellt"
		else
			echo "Fehler: Trash erstellen fehlgeschlagen"
		fi
	fi
}

function createDirFile {
	if [ -f $DIR ]; then
		echo "Dir existiert bereits"
	else
		touch $DIR
		if [ -f $DIR ]; then
			echo "Dir wurde erfolgreich erstellt"
		else
			echo "Fehler: Dir erstellen fehlgeschlagen"
		fi
	fi 
}

COUNTER=1

function moveFile {
	if [ -f $2  ]; then
		DATETIME=$(date "+%y%m%d%H%M%S")
		PID=$$
		NEWNAME=$DATETIME"_"$PID"_"$COUNTER".dat"
		mv $2 $TRASH"/"$NEWNAME
		echo "Datei wurde in den Trash verschoben"
		echo "Neuer Name:"$NEWNAME

		OLDPATH=$(realpath $2)
		echo $NEWNAME" "$OLDPATH >> $DIR

		COUNTER=$((COUNTER+1))
	else
		echo "Fehler: Es handelt sich nicht um eine Datei."

	fi
}

createTrashFolder /bin/bash
createDirFile /bin/bash

for FILE in $@
do
	moveFile /bin/bash $FILE
done

exit 0

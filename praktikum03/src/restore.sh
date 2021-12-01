#!/bin/bash

TRASH="$HOME/.trashBin"
DIR="$HOME/.trashBin/.dir"

function moveFile {
	if [ -f $TRASH"/"$2 ]; then
		LINE=$(grep $2 $DIR)
		SPLIT=( $LINE )
		OLDPATH=${SPLIT[1]}
		
		FILEDIR=$(dirname $OLDPATH)

		if [ -d $FILEDIR ]; then
			mv $TRASH"/"$2 $OLDPATH
			sed -i "/"$2"/d" $DIR
			echo "Datei erfolgreich wiederhergestellt."
		else
			echo "Fehler: Pfad existiert nicth mehr."
		fi
	else
		echo "Fehler: Datei nicht gefunden."
	fi
}

for FILE in $@
do
	moveFile /bin/bash $FILE
done

exit 0

#!/bin/sh

wget https://launchermeta.mojang.com/mc/game/version_manifest.json
cat version_manifest.json | grep -ohP '((("id": "))((?!").)+")' > versions.list
sed -i 's/"//g' versions.list
sed -i 's/id: //g' versions.list
rm version_manifest.json

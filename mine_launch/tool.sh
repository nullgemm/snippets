#!/bin/sh

# config
procyon_version="0.5.36"
output=output

# script
bitbucket=https://bitbucket.org/mstrobel/procyon/downloads/
procyon=procyon-decompiler-$procyon_version.jar

bootstrap=http://s3.amazonaws.com/Minecraft.Download/launcher/Minecraft.jar
launcher=https://s3.amazonaws.com/Minecraft.Download/launcher/launcher.pack.lzma

clean="clean"
download="download"
decompile="decompile"

mkdir -p $output

if test "$clean" = "$1"
then
echo "removing all files"
rm -rf ./$output
fi

if test "$download" = "$1"
then
echo "downloading launcher"
wget -q --directory-prefix $output $launcher
echo "downloading bootstrapper"
wget -q --directory-prefix $output $bootstrap
echo "downloading procyon"
wget -q --directory-prefix $output $bitbucket$procyon

echo "extracting launcher (lzma)"
lzmadec $output/launcher.pack.lzma > $output/launcher.pack
echo "unpacking launcher (pack200)"
unpack200 $output/launcher.pack $output/launcher.jar
echo "removing intermediate files"
rm $output/launcher.pack.lzma $output/launcher.pack
fi

if test "$decompile" = "$1"
then
echo "decompiling"
java -jar $output/$procyon -jar $output/Minecraft.jar -o $output/bootstrap
java -jar $output/$procyon -jar $output/launcher.jar -o $output/launcher
fi

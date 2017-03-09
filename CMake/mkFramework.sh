#!/bin/bash

set -e
if [ -z "$1" ]
then
    echo "Usage: `basename $0` xxx.tar.gz"
    return 1
fi

mkdir -p __Imagine/Versions/4 && ln -s 4 __Imagine/Versions/Current
cp "$1" __Imagine/Versions/Current/
cd __Imagine/Versions/Current
tar xzf "$1"
rm "$1"
mv * Resources

cat > Resources/Info.plist <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundlePackageType</key>
	<string>FMWK</string>
	<key>CFBundleShortVersionString</key>
	<string>4.2.0</string>
	<key>CFBundleGetInfoString</key>
	<string>Created by hand</string>
	<key>CFBundleSignature</key>
	<string>????</string>
</dict>
</plist>
EOF

cd -
pkgbuild --identifier imaginepp.libraries --root __Imagine --install-location /Library/Frameworks/Imagine.framework `basename $1 .tar.gz`.pkg
rm -rf __Imagine

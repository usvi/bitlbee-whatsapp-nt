# bitlbee-whatsapp-nt

OK, so in this repository I will try to create a bitlbee
plugin for whatsapp. With C. Dunno what will happen. Lets see.

Why the name? It means the next try of creating bilbee
plugin for whatsapp. Because other people have tried and
projects are now non-functioning or dormant. Or written
with exotic languages. This project will die also one day
but I will try now to make it work.

## Research
### Protocol
Protocol specs for Whatsapp Web api (we will use this)
is here:
https://github.com/sigalor/whatsapp-web-reveng

### Websocket library
It seems we need Websockets library for C.

Somebody has made a list:

https://github.com/facundofarias/awesome-websockets#c

This is available on both Debian 9 and 10 and Ubuntu 16.04 LTS:
https://libwebsockets.org/

This is available on Debian 10 only:
https://github.com/tatsuhiro-t/wslay

So maybe eventually libwebsockets7 (v. 1.7.1) as in Ubuntu?

### QR-code library
Need some kind of library for QR-code authorization, one
that can output the authorization code to a .gif or .png
for authroization.

So maybe minimum libqrencode3 as it is also with that old Ubuntu LTS?

http://megaui.net/fukuchi/works/qrencode/index.en.html

### PNG library

The QR code needs to be actually outputted as a valid format.
PNG is cool. So its something like libpng16. Exists also in that old
LTS.

http://libpng.org/pub/png/libpng.html

### AES library
Some kind of AES library is needed probably. This looks good:
https://github.com/kokke/tiny-AES-c

## Ideas / random thoughts
Make test binary for writing big arbitrary QR code PNG files.

Make test binary for authorizing clients. It will store
encryption keys which can be transferred to the plugin resource directory.
Or via irc AUTH? Need to think a bit.

Build system should be more or less the same as with bitlbee-facebook,
right? I have never used anything like this before, only pure makefiles.

Best to start on Ubuntu 16.04 LTS. Then learn autogen/autowhatever
framework by copying and modifying files until shit compiles.
There were alternatives, but better not rock the boat with something
different from for example bitlbee-facebook.

Confirming from Debian 10 that autogen.sh is successful. Going back
to Ubuntu 16.04 to continue development though.

It seems Whatsapp Web version keeps changing, so keep it configurable
easily.

Damn, things are getting so fragmented if we keep clinging on
Ubuntu 16.04 LTS. We already needed, or "needed" external curve 25519 and
base64 libraries. A big problem will be possible SSL certificate
verification and extraction.

Good example:
https://stackoverflow.com/questions/30904560/libwebsocket-client-example

Probably even better example:
https://github.com/iamscottmoyers/simple-libwebsockets-example/blob/master/client.c

Ok nice, it seems https://www.websocket.org/echo.html works with current implemation.
And the current Whatsapp connection does not.

Why have separate setting for Whatsapp Web version? See:
https://github.com/sigalor/whatsapp-web-reveng/issues/272
It says:
"JS demo is not working
I tried to run the latest index_jsdemo.js in local and share the web session.
I am able to start the local server , the QR code that got generated is not valid to
start the web session sharing. Any idea??
You need to update Whatsapp Web version to "0,4,2081"."

Every websocket library has some stupidities so at some point I started to create my own.

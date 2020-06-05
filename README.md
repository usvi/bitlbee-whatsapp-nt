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


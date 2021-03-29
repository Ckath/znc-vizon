# znc-vizon
znc module for automatically entering the VIzon lotteries on rizon, triggered by #VIzon topic changes.

## install
```
# build .so
znc-build vizon.cpp
# copy .so to wherever .znc/modules is, for me /home/znc
cp vizon.so /home/znc/.znc/modules
```
then just load it: `/msg *status loadmod vizon`

## usage
by default random bets will be made each time, you can set a fixed bet with the same syntax you use to place regular bets: `/msg *vizon bet 1 4 7 14 22 24`, or `/msg *vizon bet random` to set it to random bets again. checking the current bet is done with `/msg *vizon check`. bets are sent to VIzon as is without checking validity so make sure they're valid.

## FAQ
- how do I stop it from entering for me?\
not, unload it with `/msg *status unloadmod vizon`
- how do I check which bets were made, and if I won?\
just use VIzon as normal: `/msg VIzon check <drawing ID>`
- vizon? rizon lottery? what?\
see the [VIzon wiki.rizon entry](https://wiki.rizon.net/index.php?title=Vizon) for info about the actual lottery game, this is just a module that enters for you

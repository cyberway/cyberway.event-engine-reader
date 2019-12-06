# cyberway.event-engine-reader
Service to print cyberway events to stdout

### prototype usage

0. Build
1. Start nodeos with `event-engine-plugin` enabled and event set:
```
nodeos \
--plugin eosio::event_engine_plugin \
--event-engine-unix-socket /tmp/msg.sock
…other options…
```
2. Start 
```
cyberway.event-engine-reader /tmp/msg.sock
```
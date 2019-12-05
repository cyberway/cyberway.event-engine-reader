# cyberway.event-engine-reader
Service to print cyberway events to stdout

### prototype usage

1. Build
2. Start nodeos with `event-engine-plugin` enabled and event set:
```
nodeos -e -p eosio \
--plugin eosio::event_engine_plugin \
--event-engine-dumpfile ./events.txt \
…other options…
```

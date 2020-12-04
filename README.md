# Base station implementation for modified LEACH protocol
This repo will contain necessary files for LEACH protocol implementation of base station.

Once booted up, base station will connect to MQTT server, and open UDP broadcast port
for listening. Once packet arrives from cluster heads of nodes, base station will parse
that packet and update topics related to nodes data. If base station disconnects from
MQTT server, it will retry connection each 5 seconds.

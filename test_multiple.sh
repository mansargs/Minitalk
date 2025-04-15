#!/bin/bash

# Save the path to the client program
CLIENT="./user"

# Check if client executable exists
if [ ! -f "$CLIENT" ]; then
    echo "Error: client program '$CLIENT' not found."
    exit 1
fi

# Get server PID (must be running already)
read -p "Enter your SERVER PID: " SERVER_PID

# Check if PID is valid
if ! kill -0 "$SERVER_PID" 2>/dev/null; then
    echo "Error: Server with PID $SERVER_PID is not running."
    exit 1
fi

# Define test messages
messages=(
    "Hello from Alice"
    "Bob here with a message"
    "Charlie is testing"
    "Data from Delta"
    "Echo says hi!"
    "Foxtrot sending text"
    "Golf is alive"
    "Hotel transmitting..."
    "India sends greetings"
    "Juliet joined the test"
)

# Launch each client in the background
for msg in "${messages[@]}"
do
    echo "Sending: \"$msg\""
    $CLIENT "$SERVER_PID" "$msg" &
done

# Wait for all background processes to finish
wait
echo "All clients finished."


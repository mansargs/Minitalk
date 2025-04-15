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

# Define test messages with Unicode and longer content
messages=(
    "🌐 This is a transmission from the International Space Research Station 🛰️ orbiting Earth at 7.66 km/s. All systems are nominal. Atmospheric scans show no anomalies, and our crew of 12 is safe and well. 🌌 Sending greetings to all connected nodes! 🌍👩‍🚀👨‍🚀"
    "📡📶 Incoming data stream from Deep Space Probe ✨ Voyager-9: Particle density measurements, magnetic field data, and radiation levels are being uploaded at 128 Mbps. 👨‍🔬 Please verify checksum and confirm successful receipt of data blocks 0241–0287. ✅🧬"
    "🚀 Mission Log Entry #3482 — Commander Rhea reporting: We have officially entered the orbit of Kepler-452b. The exoplanet’s terrain appears mountainous with traces of ice caps. 🌋🗻 Our drones are being deployed for surface analysis. 🌡️📷"
    "🔒 Security Alert! Unrecognized access attempt detected from IP range 🌐 192.52.108.44/27. 🚨 Immediate lockdown protocols have been initiated. Please confirm the legitimacy of this device using biometric authentication or security token verification. 🔐👁️"
    "🎮 Player 0782 completed the Hidden Quest: 'The Lantern of Myths' 🔦 in record time! Total XP gained: 6,720. Loot acquired: Enchanted Bow 🏹, 4x Mana Elixir 💧, and a mysterious rune stone 🪨. Achievements unlocked: 'Seeker of Shadows', 'Speed Demon'. 🏆"
    "📊 Network Monitoring Update: Node-27 has reported packet loss exceeding 12% over the last 15 minutes. 📉 Traceroute diagnostics in progress. Potential causes: 🧱 firewall misconfig, 🌩️ unstable routing path, or 🐞 firmware bug. Awaiting engineering input..."
    "🎓 Welcome to the Intergalactic Linguistics Symposium 2297 🪐 — Today's keynote by Dr. Axara Zyy: 'The Semantics of Silence in Non-Phonetic Civilizations'. Topics include: 👄 telepathic grammar, ✨ quantum syntax, and 🌀 zero-verbal negotiation strategies."
    "📦 Archive Log: Artifact #992A-TQ recovered from ruins beneath ocean trench 🌊 near coordinates 27.3°S, 68.1°W. Composition: unknown metal alloy. Inscriptions: non-linear script. Current location: Deep Containment Vault B-3. Clearance Level: Ω required. 🧊🔍"
    "🌲🦉 Wilderness Beacon Signal: Expedition Team Alpha has reached the northern perimeter of Bio-Zone Delta. Biodiversity index has surpassed expectations. Species logged: 72, including previously undocumented flora with bioluminescent properties. 🌱✨"
    "📅 Historical Upload Initiated — Year 2487, Unified Earth Archive: 'The Day the Skies Went Dark'. 🕯️ A full retelling of the solar flare event, its impact on Earth's magnetosphere, and the 42-hour global blackout that followed. Primary source logs restored."
)


# Launch each client in the background
for msg in "${messages[@]}"
do
    echo "Sending: \"$msg\""
    $CLIENT "$SERVER_PID" "$msg" &
done

# Wait for all background processes to finish
echo "All clients finished."

str = "\"hello\": \"world\" \"howa\": \"you\""

buffer = ""
mode = ""
read = 0

commands = []
new_command = {"url": "", "path": ""}
for i in range(len(str)):
    c = str[i]
    if c == "\"" and mode == "string":
        if read % 2 == 0:
            new_command["url"] = buffer
        else:
            new_command["path"] = buffer
            commands.append({
                "url": new_command["url"],
                "path": new_command["path"]
                })
        read += 1
        mode = "eofString"
        print(buffer)
        buffer = ""
        mode = ""
        continue
    elif c == "\"":
        mode = "string"
        continue

    if mode == "string":
        buffer += c

print(commands)

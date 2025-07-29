#ifndef WEB_PAGE_H
#define WEB_PAGE_H

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Wi-Chalkboard</title>
  <meta name='viewport' content='width=device-width, initial-scale=1'>
  <style>
    body { font-family: sans-serif; padding: 20px; }
    textarea { width: 100%; height: 80px; }
    ul { list-style: none; padding: 0; }
    li { margin: 10px 0; background: #eee; padding: 10px; border-radius: 5px; }
  </style>
</head>
<body>
  <h2>🧠 Wi-Chalkboard</h2>
  <form action='/submit' method='POST'>
    <textarea name='message' placeholder='Write your message...'></textarea><br><br>
    <input type='submit' value='Post Message'>
  </form>
  <hr>
  <h3>📝 Recent Messages:</h3>
  <ul>
    %MESSAGES%
  </ul>
</body>
</html>
)rawliteral";

#endif

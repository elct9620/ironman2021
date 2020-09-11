# frozen_string_literal: true

while true
  clear
  draw_text "Hello World", i, 8
  i += 1
  sleep 100
  i = 0 if i == 2
end

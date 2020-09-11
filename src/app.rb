# frozen_string_literal: true

i = 0
while true
  clear
  draw_text "Hello World", i, 8
  i += 2
  sleep 100
  i = i % 128
end

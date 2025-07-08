{
  "targets": [
    {
      "target_name": "usocket",
      "sources": ["src/usocket.cc"],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -e \"require('node-addon-api').gyp\")"
      ],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
      "conditions": [
        ["OS=='linux' or OS=='freebsd' or OS=='openbsd' or OS=='sunos' or OS=='aix'", {
          "cflags_cc": ["-std=c++17"]
        }]
      ]
    }
  ]
}
module.exports =
  dev:
    options:
      mangle: false,
      beautify: true
    files:
      "./assets/scripts/application.dist.js": ["./build/assets/scripts/application.js"]
  dist:
    options:
      beautify: false,
      mangle: false
    files:
      "./assets/scripts/application.dist.js": ["./build/assets/scripts/application.js"]

module.exports =
  dist:
    files:
      "./assets/stylesheets/application.suit.css":
        [
          "./build/assets/stylesheets/application.css"
        ]
  conformance:
    files:
      "./source/assets/stylesheets/conformance.css": [
        "./assets/stylesheets/layout/component.json"
        "./components_local/**/component.json"
        "!./components_local/sponsor/component.json"
      ]

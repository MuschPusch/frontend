module.exports = {
  dist: {
    files: {
      "assets/stylesheets/application.css": ["component.json"]
    },
    options: {
      resolveOpts: {
        install: true,
        out: "components"
      }
    }
  }
};

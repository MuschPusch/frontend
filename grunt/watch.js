module.exports = {
  css: {
    tasks: ["suitcss"],
    files: ["./components_local/**/*.css", "./index.css", "./theme/**/*.css"]
  },
  js: {
    tasks: ["componentbuild"],
    files: ["./components_local/**/*.js", "./index.js"]
  }
};

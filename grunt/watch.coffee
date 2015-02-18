module.exports=
  suitcss:
    files: [
      './assets/stylesheets/application.css'
      './assets/stylesheets/base/*.css'
      './assets/stylesheets/drupal/*.css'
      './assets/stylesheets/layout/*.css'
      './components_local/**/*.css'
    ]
    tasks: [
      'duojs:css'
      'suitcss:dist'
    ]
  suitjs:
    files: [
      './assets/scripts/application.js'
      './components_local/**/*.js'
    ]
    tasks: [
      'duojs:js'
      'uglify:dev'
    ]

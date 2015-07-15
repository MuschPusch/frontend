module.exports = {
  symbol: {
    cwd: 'assets/svg_sprite/input',
    src: ['**/*.svg'],
    dest: 'assets/svg_sprite/output',
    options: {
      mode: {
        symbol: {
          render: {
            css: true
          },
          example: true
        }
      }
    }
  }
};

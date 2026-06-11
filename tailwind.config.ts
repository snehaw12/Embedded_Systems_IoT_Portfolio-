import type { Config } from 'tailwindcss';

const config: Config = {
  content: ['./app/**/*.{ts,tsx}', './components/**/*.{ts,tsx}'],
  theme: {
    extend: {
      colors: {
        cinematic: '#040407',
        accent: '#f97316',
        glow: '#93c5fd'
      }
    }
  },
  plugins: []
};

export default config;

# Cinematic Next.js Portfolio

Production-ready Next.js 14 portfolio with a cinematic fullscreen hero built for Vercel deployment.

## Stack

- Next.js 14+ App Router (TypeScript)
- Tailwind CSS
- GSAP animations
- Three.js particle background

## Included Features

- Fullscreen video hero with ambient blur and dark cinematic palette (`#040407`)
- Glassmorphic controls (play/pause, mute/unmute)
- Floating bokeh particles (orange `#f97316` + blue `#93c5fd`) with mouse parallax
- Staggered GSAP entrance animation
- Scroll indicator with pulse animation
- Mobile responsive layout
- Proper Three.js cleanup in `useEffect` teardown
- Sound hint auto-hide

## Local setup

```bash
npm install
npm run dev
```

Open `http://localhost:3000`.

## Production checks

```bash
npm run lint
npm run build
```

## Video setup

1. Keep placeholder file at `public/hero-video.mp4` or replace it with your final MP4.
2. Optionally set a CDN/video URL in `.env.local`:

```bash
NEXT_PUBLIC_HERO_VIDEO=/hero-video.mp4
```

If `.env.local` is missing, the app defaults to `/hero-video.mp4`.

## Deploy on Vercel

1. Push this repository to GitHub.
2. Import the repository in Vercel.
3. Add `NEXT_PUBLIC_HERO_VIDEO` in Vercel Environment Variables if using hosted video.
4. Deploy.

No extra server configuration is required.

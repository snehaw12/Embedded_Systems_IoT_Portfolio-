'use client';

import { useEffect, useMemo, useRef, useState } from 'react';
import styles from './Hero.module.css';

export default function VideoIntro() {
  const videoRef = useRef<HTMLVideoElement>(null);
  const [isPlaying, setIsPlaying] = useState(true);
  const [isMuted, setIsMuted] = useState(true);
  const [showHint, setShowHint] = useState(true);
  const videoSrc = useMemo(() => process.env.NEXT_PUBLIC_HERO_VIDEO || '/hero-video.mp4', []);

  useEffect(() => {
    const timer = window.setTimeout(() => setShowHint(false), 3200);
    return () => window.clearTimeout(timer);
  }, []);

  const togglePlay = async () => {
    if (!videoRef.current) return;

    if (videoRef.current.paused) {
      await videoRef.current.play().catch(() => undefined);
      setIsPlaying(true);
      return;
    }

    videoRef.current.pause();
    setIsPlaying(false);
  };

  const toggleMute = () => {
    if (!videoRef.current) return;
    videoRef.current.muted = !videoRef.current.muted;
    setIsMuted(videoRef.current.muted);
  };

  return (
    <div className={styles.videoWrap}>
      <video
        ref={videoRef}
        className={styles.video}
        autoPlay
        loop
        muted
        playsInline
        preload="metadata"
        onPause={() => setIsPlaying(false)}
        onPlay={() => setIsPlaying(true)}
      >
        <source src={videoSrc} type="video/mp4" />
      </video>
      <div className={styles.videoOverlay} />

      <div className={styles.controls}>
        <button type="button" className={styles.controlBtn} onClick={togglePlay} aria-label="Toggle playback">
          {isPlaying ? 'Pause' : 'Play'}
        </button>
        <button type="button" className={styles.controlBtn} onClick={toggleMute} aria-label="Toggle mute">
          {isMuted ? 'Unmute' : 'Mute'}
        </button>
      </div>

      {showHint && <p className={styles.soundHint}>Sound available · tap unmute</p>}
    </div>
  );
}

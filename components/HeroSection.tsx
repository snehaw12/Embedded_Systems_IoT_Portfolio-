'use client';

import { useEffect, useRef } from 'react';
import gsap from 'gsap';
import styles from './Hero.module.css';
import VideoIntro from './VideoIntro';
import CinematicParticles from './CinematicParticles';

export default function HeroSection() {
  const heroRef = useRef<HTMLElement>(null);

  useEffect(() => {
    if (!heroRef.current) return;

    const ctx = gsap.context(() => {
      gsap.fromTo(
        `.${styles.reveal}`,
        { opacity: 0, y: 30 },
        { opacity: 1, y: 0, stagger: 0.12, duration: 1.1, ease: 'power3.out', delay: 0.25 }
      );

      gsap.to(`.${styles.scrollDot}`, {
        y: 10,
        repeat: -1,
        yoyo: true,
        duration: 1.1,
        ease: 'sine.inOut'
      });
    }, heroRef);

    return () => ctx.revert();
  }, []);

  return (
    <section className={styles.hero} ref={heroRef}>
      <VideoIntro />
      <div className={styles.ambientLayer} />
      <CinematicParticles />

      <div className={styles.content}>
        <p className={`${styles.tagline} ${styles.reveal}`}>Embedded Systems · IoT · Firmware</p>
        <h1 className={`${styles.name} ${styles.reveal}`}>
          <span>Sneha</span>
          <span>Wanave</span>
        </h1>
        <p className={`${styles.role} ${styles.reveal}`}>
          M.Sc. Electrical Engineering &amp; Embedded Systems
        </p>
        <p className={`${styles.location} ${styles.reveal}`}>
          📍 RWU Weingarten, Germany · Werkstudent Open
        </p>

        <div className={`${styles.ctaRow} ${styles.reveal}`}>
          <a href="#projects" className={styles.primaryBtn}>
            View Projects
          </a>
          <a href="mailto:sneha@example.com" className={styles.secondaryBtn}>
            Hire Me
          </a>
        </div>
      </div>

      <div className={styles.scrollIndicator} aria-hidden>
        <span className={styles.scrollDot} />
      </div>
    </section>
  );
}

'use client';

import { useEffect, useRef } from 'react';
import * as THREE from 'three';
import styles from './Hero.module.css';

type ParticlesMeta = {
  camera: THREE.PerspectiveCamera;
  points: THREE.Points;
};

export default function CinematicParticles() {
  const mountRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const mountNode = mountRef.current;
    if (!mountNode) return;

    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.z = 50;

    const renderer = new THREE.WebGLRenderer({ alpha: true, antialias: true });
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
    renderer.setSize(window.innerWidth, window.innerHeight);
    mountNode.appendChild(renderer.domElement);

    const count = 420;
    const positions = new Float32Array(count * 3);
    const colors = new Float32Array(count * 3);
    const orange = new THREE.Color('#f97316');
    const blue = new THREE.Color('#93c5fd');

    for (let i = 0; i < count; i += 1) {
      const i3 = i * 3;
      positions[i3] = (Math.random() - 0.5) * 140;
      positions[i3 + 1] = (Math.random() - 0.5) * 90;
      positions[i3 + 2] = (Math.random() - 0.5) * 80;

      const mixed = orange.clone().lerp(blue, Math.random());
      colors[i3] = mixed.r;
      colors[i3 + 1] = mixed.g;
      colors[i3 + 2] = mixed.b;
    }

    const geometry = new THREE.BufferGeometry();
    geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));

    const material = new THREE.PointsMaterial({
      size: 1.7,
      transparent: true,
      opacity: 0.8,
      depthWrite: false,
      vertexColors: true,
      blending: THREE.AdditiveBlending
    });

    const points = new THREE.Points(geometry, material);
    scene.add(points);

    const state: ParticlesMeta = { camera, points };
    let mouseX = 0;
    let mouseY = 0;

    const onMouseMove = (event: MouseEvent) => {
      mouseX = (event.clientX / window.innerWidth - 0.5) * 2;
      mouseY = (event.clientY / window.innerHeight - 0.5) * 2;
    };

    const onResize = () => {
      state.camera.aspect = window.innerWidth / window.innerHeight;
      state.camera.updateProjectionMatrix();
      renderer.setSize(window.innerWidth, window.innerHeight);
    };

    let frameId = 0;
    const animate = () => {
      frameId = requestAnimationFrame(animate);
      state.points.rotation.y += 0.0009;
      state.points.rotation.x += 0.00035;
      state.points.position.x += (mouseX * 3 - state.points.position.x) * 0.035;
      state.points.position.y += (-mouseY * 3 - state.points.position.y) * 0.035;
      renderer.render(scene, state.camera);
    };

    animate();
    window.addEventListener('resize', onResize);
    window.addEventListener('mousemove', onMouseMove);

    return () => {
      cancelAnimationFrame(frameId);
      window.removeEventListener('resize', onResize);
      window.removeEventListener('mousemove', onMouseMove);
      geometry.dispose();
      material.dispose();
      renderer.dispose();
      mountNode.removeChild(renderer.domElement);
    };
  }, []);

  return <div ref={mountRef} className={styles.particles} aria-hidden />;
}

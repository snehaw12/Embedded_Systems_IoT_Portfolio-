import type { Metadata } from 'next';
import './globals.css';

export const metadata: Metadata = {
  title: 'Sneha Wanave | Embedded Systems Portfolio',
  description: 'Cinematic embedded systems and IoT portfolio.'
};

export default function RootLayout({
  children
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body>{children}</body>
    </html>
  );
}

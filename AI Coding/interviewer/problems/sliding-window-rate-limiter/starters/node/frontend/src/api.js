const API_URL = import.meta.env.VITE_API_URL ?? '/api';

export async function checkRequest(now) {
  const response = await fetch(`${API_URL}/rate-limits/check`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ now })
  });
  if (!response.ok) throw new Error('Rate-limit check failed');
  return response.json();
}

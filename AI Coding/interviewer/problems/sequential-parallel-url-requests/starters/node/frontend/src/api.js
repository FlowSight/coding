const API_URL = import.meta.env.VITE_API_URL ?? '/api';
export async function runSequentialRequests(urls) {
  const response = await fetch(`${API_URL}/requests/sequential`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ urls })
  });
  if (!response.ok) throw new Error('URL request job failed');
  return response.json();
}

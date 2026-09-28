const API_URL = import.meta.env.VITE_API_URL ?? '/api';
export async function addRoute(pattern, handler) {
  const response = await fetch(`${API_URL}/router/routes`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ pattern, handler })
  });
  if (!response.ok) throw new Error('Could not add route');
}
export async function matchPath(path) {
  const response = await fetch(`${API_URL}/router/match?path=${encodeURIComponent(path)}`);
  if (!response.ok) throw new Error('Could not match path');
  return response.json();
}

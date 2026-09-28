export async function analyzeShards(shards) {
  const response = await fetch('http://localhost:8080/api/diagnostics/analyze', { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(shards) });
  if (!response.ok) throw new Error('Diagnostics request failed');
  return response.json();
}

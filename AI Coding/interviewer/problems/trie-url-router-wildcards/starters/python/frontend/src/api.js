export async function addRoute(pattern, handler) {
  const response = await fetch("/api/router/routes", {
    method: "POST", headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ pattern, handler }),
  });
  if (!response.ok) throw new Error("Could not add route");
}

export async function matchPath(path) {
  const response = await fetch(`/api/router/match?path=${encodeURIComponent(path)}`);
  if (!response.ok) throw new Error("Could not match path");
  return response.json();
}

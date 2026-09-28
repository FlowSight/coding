import React,{useState} from 'react'; import {filterEvents} from './api.js'; import EventInput from './components/EventInput.jsx';
export default function App(){const [events,setEvents]=useState([]);const [result,setResult]=useState([]);const [error,setError]=useState('');
async function run(){try{setError('');setResult(await filterEvents(events));}catch(e){setError(e.message);}}
return <main><h1>Event Validation Console</h1><EventInput onAdd={e=>setEvents([...events,e])}/><p>{events.length} queued events</p><button onClick={run}>Filter batch</button>{error&&<p>{error}</p>}<pre>{JSON.stringify(result,null,2)}</pre></main>}

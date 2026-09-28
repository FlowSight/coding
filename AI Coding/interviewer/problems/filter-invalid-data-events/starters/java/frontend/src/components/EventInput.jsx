import React,{useState} from 'react';
export default function EventInput({onAdd}){const [id,setId]=useState('');const [payload,setPayload]=useState('');
return <section><input placeholder="Event id" value={id} onChange={e=>setId(e.target.value)}/><input placeholder="Payload" value={payload} onChange={e=>setPayload(e.target.value)}/><button onClick={()=>onAdd({id,type:'click',payload,timestampMillis:Date.now()})}>Queue event</button></section>}

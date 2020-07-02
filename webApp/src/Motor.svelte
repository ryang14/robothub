<script>
  export let port;

  let portInt16 = new Int16Array(port.buffer);
  let speed = portInt16[1];
  let position = portInt16[2];
</script>

<style>
  input {
    width: 2rem;
    margin: 0.1rem;
  }
</style>

<div>
  <div>Motor:</div>
  <label for="speed">Speed:</label>
  <input type="number" id="speed" bind:value={speed} min="0" max="65535" />
  <label for="Position">Position:</label>
  <input
    type="number"
    id="position"
    bind:value={position}
    min="0"
    max="65535" />
</div>

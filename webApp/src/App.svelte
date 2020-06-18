<script>
  import Ports from "./Ports.svelte";

  const fetchPortData = (async () => {
    const response = await fetch("/ports.json");
    return await response.json();
  })();
</script>

<style>
  main {
    text-align: center;
    padding: 1em;
    max-width: 240px;
    margin: 0 auto;
  }

  @media (min-width: 640px) {
    main {
      max-width: none;
    }
  }
</style>

<main>
  {#await fetchPortData}
    <p>...waiting</p>
  {:then data}
    <Ports ports={data} />
  {:catch error}
    <p>An error occurred!</p>
  {/await}
</main>

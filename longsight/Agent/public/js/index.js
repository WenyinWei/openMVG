function onCaptureButtonPress() {
  const { location } = window;
  const url = location.href.replace(/4000/, 4001);
  fetch(`${url}capture`, { mode: "no-cors" });
}

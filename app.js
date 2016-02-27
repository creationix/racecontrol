function call(name, value) {
  console.log("Calling", name, value);
  var xhr = new XMLHttpRequest();
  var url = "https://api.particle.io/v1/devices/53ff6c065075535120151387/" + name;
  xhr.open("POST", url);
  xhr.setRequestHeader("Authorization", "Bearer 88c64f5c7de12db5af94479c92e6b0d5fd9db6dd");
  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhr.send("arg=" + value);
}

window.onload = function () {
  "use strict";
  var img = document.querySelector("img");
  var canvas = document.createElement('canvas');
  canvas.width = img.width;
  canvas.height = img.height;
  var context = canvas.getContext('2d');
  context.drawImage(img, 0, 0, img.width, img.height);
  canvas.onclick = canvas.ontouch = function (event) {
    var pixelData = context.getImageData(event.offsetX, event.offsetY, 1, 1).data;
    var color =
      (pixelData[0] << 16) |
      (pixelData[1] << 8) |
      pixelData[2];
    console.log(color.toString(16));
    call("color", color);
    document.body.style.backgroundColor = "#" + color.toString(16);
  };
  document.body.removeChild(img);
  document.body.appendChild(canvas);


  var canvas2 = document.createElement('canvas');
  canvas2.width = window.innerWidth;
  canvas2.height = 30;
  var ctx = canvas2.getContext('2d');
  var grd = ctx.createLinearGradient(0,0,canvas2.width,0);
  grd.addColorStop(0,"black");
  grd.addColorStop(1,"white");
  ctx.fillStyle = grd;
  ctx.fillRect(0, 0, canvas2.width, canvas2.height);
  canvas2.onclick = canvas2.ontouch = function (event) {
    var pixelData = ctx.getImageData(event.offsetX, event.offsetY, 1, 1).data;
    var color =
      (pixelData[0] << 16) |
      (pixelData[1] << 8) |
      pixelData[2];
    call("speed", pixelData[0] >> 2);
    document.body.style.backgroundColor = "#" + color.toString(16);
  };
  document.body.appendChild(canvas2);
};

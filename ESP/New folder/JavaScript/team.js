/**========================================================================
 *                           Navbar
 *========================================================================**/
function showSidebar() {
    const sidebar = document.querySelector('.sidebar');
    sidebar.style.display = 'flex';
  }
  function hideSidebar() {
    const sidebar = document.querySelector('.sidebar');
    sidebar.style.display = 'none';
  }
  /*============================ END OF Nabbar ============================*/
  /**------------------------------------------------------------------------
 *                           TIME AND DATE
 *------------------------------------------------------------------------**/

function formatWithLeadingZero(number) {
    return number < 10 ? `0${number}` : number;
  }
  function updateDateTime() {
    const now = new Date(); // Get the current date and time
    let hours = now.getHours();
    const minutes = formatWithLeadingZero(now.getMinutes());
    const seconds = formatWithLeadingZero(now.getSeconds());
    const amPm = hours >= 12 ? 'PM' : 'AM';
    hours = hours % 12 || 12;
    const dateTimeString = `${now.toDateString()} || ${hours}:${minutes} ${amPm}`;
    document.getElementById('DateTime').textContent = dateTimeString;
  }
  
  // Update the date and time every second
  setInterval(updateDateTime, 1000);
  
  // Initial update
  updateDateTime();
    /*============================ END OF TIME AND DATE ============================*/

    setTimeout(showfoot, 1000); //autohide foot in 1sec

    document.getElementById('hidefoot').addEventListener('click', showfoot)
    
    
    function showfoot() {
      var but = document.getElementById('hidefoot');
      var foot = document.getElementById('hidethis');
      if (but.innerHTML === 'hide') {
        but.innerHTML = 'show';
      }
      else {
        but.innerHTML = 'hide';
      }
      foot.classList.toggle('inactive');
    }
    
    
    function validateInput(input, max) {
      if (parseInt(input.value) > max) {
        input.value = max;
      }
    }
    
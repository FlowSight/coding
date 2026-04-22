Implement a wishlist feature using JavaScript that initially displays 5 rows of data. Each row consists of a product ID, product name, and a 'wishlist' button. On clicking the 'wishlist' button, show 'Added to wishlist' and change the button text to 'Remove from wishlist'; clicking again should restore it to the original state.

Additionally, there should be a 'load more' button below the list, which loads 5 more rows into the list upon clicking. The top of the list should display the current number of rows. When the number of rows reaches 30, the 'load more' button should become disabled.

Requirements:

Use Vanilla JS only, no frameworks allowed.
Example: Assume initial data is structured like the following:

[{ productId: '1', productName: 'Product 1' }, { productId: '2', productName: 'Product 2' }, ... ]
After pressing 'load more', new rows should append in the same format and update the row counter.
/* Writen by Alex Luong
 * Test DA class */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "da.h"
#include "integer.h"

static void displayItems(DA *);
static void visualizeItems(DA *);
static void testInsertAndRemove(DA *);
static void testSetAndGet(DA *);
static void testUnion(DA *, DA *);
static void testExtract(DA *);

int main(void) {
  int i;
  DA *items = newDA(displayInteger);
  testInsertAndRemove(items);

  // Currently, items = [][1]
  testSetAndGet(items);

  // Set up recipient and donor
  DA *recipient = newDA(displayInteger);
  for (i = 0; i < 4; i++)
    insertDA(recipient, newInteger(i));

  DA *donor = newDA(displayInteger);
  for (i = 0; i < 5; i++)
    insertDA(donor, newInteger(i));

  // Test union
  testUnion(recipient, donor);

  testExtract(recipient);

  return 0;
}

static void testInsertAndRemove(DA *items) {
  int i;

  // Display an empty DA
  displayItems(items);

  printf("\n");

  // Put 100 values in the array
  for (i = 0; i < 100; i++)
    insertDA(items, newInteger(i));
  displayItems(items);
  visualizeItems(items);
  printf("\n");

  // Remove the last value
  printf("The value ");
  displayInteger(stdout, removeDA(items));
  printf(" was removed.\n");
  printf("\n");

  // Remove the rest
  for (i = 0; i < 99; i++)
    removeDA(items);
  displayItems(items);
  visualizeItems(items);
  printf("\n");
}

static void testSetAndGet(DA *items) {
  insertDA(items, newInteger(1));
  visualizeItems(items);
  int x = getInteger((integer *) getDA(items,0));
  printf("The first item is %d.\n", x);
  setDA(items, 0, newInteger(2));
  printf("After set:\n");
  visualizeItems(items);
  printf("\n");
}

static void testUnion(DA *recipient, DA *donor) {
  // Union
  unionDA(recipient, donor);

  // Show donor
  printf("Donor:\n");
  displayItems(donor);
  visualizeItems(donor);
  printf("\n");

  // Show recipient
  printf("Recipient:\n");
  displayItems(recipient);
  visualizeItems(recipient);
  printf("\n");
}

static void testExtract(DA *items) {
  // Extract
  int size = sizeDA(items);
  void **array = extractDA(items);
  printf("Recipient after extracting:\n");
  visualizeItems(items);
  printf("\n");

  printf("The last item in the extracted array is %d\n", getInteger((integer *)array[size-1]));
}

static void displayItems(DA *items) {
  printf("displayItems: ");
  displayDA(stdout,items);
  printf("\n");
}

static void visualizeItems(DA *items) {
  printf("visualizeItems: ");
  visualizeDA(stdout,items);
  printf("\n");
}